# Simple Server Interactions
This exercise will continue our guidance through the A3 assignment. It 
presupposes that you have completed the subtasks described in the previous
exercise. You will also need to consult the handout for A3 for technical 
descriptions of the protocol and system as a whole.

Note, you do not need to follow this guide if you have your own ideas about 
how to solve A3. Additionally, this is not intended as a complete guide to 
every line you will need to write. It will describe much of the general 
structure and provide some specific functions as assistance, but you will need
to flesh out the bones provided here.

Finally, do note that not all of the tasks described in these guides are equal.
Some will take considerably longer than others and so if you finish these all 
very quickly feel free to move on to the next ahead of time. 

## Setting Up Server Threading
Having previously set up the core client interactions in the previous 
exercise, we will now begin to set up some server interactions. Currently, the 
server side of the peer barely does anything, just starting, printing that it 
is done and then finishing. We need it to be capable of receiving requests 
from other peers, and for doing so in a non-blocking manner. This will require 
some threading, with inbound connections handed off to a handling thread. 

Note that as we're building a relatively small network you do not need to 
manage the amount of threads you are creating here, we will just start as many 
threads as we receive connections as we should never receive that many 
connections at once.

You can look to the exercises from the 'Network Programming' lecture to get 
some guiding examples on how to set up a non-blocking server. In summary, you 
will need to create a listening port for other servers to contact initially. 
If you wish to use the _compsys_helper_open_listenfd_ function (I you should), 
then you will need to convert the port stored in _my_address_ from an integer 
to a char*. You should be able to use the same code as you wrote from the 
client side of the interaction last exercise. 

Once we have set up a listening socket then it would make sense to enter a 
loop, where each iteration waits for an inbound communication attempt. As we 
accept these inbound communications we should spawn off a thread to handle 
that request. Note that we will not call _pthread_join_ on that thread, as 
that would sequentialise our code. We shall simply start the handling thread 
and then our main _server_thread_ will return to listening for new inbound 
communications. As a hint for some of the problems we will need to solve next 
week, this setup means that a single peer may have multiple handling threads 
running at the same time, which could introduce problems such as race 
conditions or deadlocks. This will be returned to within these guides, just 
keep it in mind for now.

Within your handling thread (which I called _handle_server_request_thread_) 
you should remember to call the following:

    pthread_detach(pthread_self());

This effectively makes the thread independent of the calling thread so we 
don't need to call pthread_join in order to properly clean up once it is done. 

Any time we are invoking our handling thread, it is because someone is sending 
us a message, which we should probably read. In order to do this we should use 
the _compsys_helper_readnb_ function to read our message into a 
pre-initialised buffer. We can use the same logic we've previously used in 
reading our responses to parse our reading the initial request. We don't know 
the entire content of the message, but we know that any request we will 
receive will be using the same Request Header, with a length given to us by 
the _REQUEST_HEADER_LEN_ variable. We can read the header into the 
_RequestHeader_ struct also using very similar logic as reading the response, 
though do make sure to now the differences in what fields are included and 
where in the message.

Once we have read the header we know how long the body (if any) there is to 
read, so we should make sure to read that too if there is one. We may also 
wish at this stage to perform input validation, such as does the header 
specify a valid command and such like.

## Handling Register Requests
Now that we have some very basic server interactions it's time to start 
implementing the other half of the interaction we made last exercise, e.g. to 
actually parse a register request from another peer and to generate a response 
to it. To test this you could run either the Python peer, or your C peer and 
try and get it to connect to your implementation.

From the previous task we should already have the initial reading of the 
request, by parsing the header. You may wish to introduce a new function to 
handle the register messages, or you many wish to keep it all within your 
larger handling thread. 

Make sure that before you do any actual registration handling you perform some 
input validation. Within 'common.c' there are the functions _is_valid_ip_, 
_is_valid_port_, and _is_valid_port_str_ that may help with this. You should 
also validate that you are not registering a peer that is already in the 
network.

Assuming the registration request is validly formatted, then your peer should 
create a new _NetworkAddress_ struct to store the peer details. The IP and 
port should just be copied from the message, but we will not save the 
peer-provided signature directly. Instead, we are to salt and hash the 
provided signature into a network-saved signature.

This time, rather than a hard coded salt we are going to randomly generate it. 
For this we can use the _generate_random_salt_ function, as well as the logic 
you have used for generating user signatures. You may need to tweak any 
signature generating function slightly to accommodate some potentially 
different input datatypes. Only the salted and hashed signature should be 
saved in the peer _NetworkAddress_ struct, along with the randomly generated 
salt.

Finally, you should append the peer _NetworkAddress_ to the global _network_ 
variable. Make sure to update the _peer_count_ variable as appropriate too. 
Note that according to the protocol at this stage we should also be generating 
an Inform message for each of the other peers on the network, but we will hold 
off on doing that until next exercise.

## Generating Register Responses
Part of the protocol description is that a response is always expected to a 
registration request. We should therefore create such a response. There are 
two parts to this, generating the message content to send, and creating a 
function for assembling reply messages. 

Generating the actual message content should be reasonably straight forward. 
You just need to copy each network entry to one large buffer, and then this 
can become the message body. Make sure to consult with the A3 handout if you 
need to check which element goes where in the message body.

Now to send the actual message itself you will need to assemble a header. As 
we may wish to send several different types of response message, I think it is 
worth creating another function to generically create response messages. The 
signature I used was ended up like so:

    void send_response(uint32_t connfd, uint32_t status, char* response_body, int response_length)

You may of course differ from this if you wish. For the time being we can 
ignore the possibility of a response being need to be sent over several 
messages and assume that it will all fit in one. In this case, we just need to 
assemble a single instance of the _ReplyHeader_ struct, remembering to ensure 
all the numeric values are in the correct byte ordering. Also note that if the 
message is being sent over only a single message, then the _total_hash_ and 
_block_hash_ will have identical values. Once you have assembled your header 
and body, you should write them to the connection.

If you have not done so already, make sure that you close the connection in 
your request handling thread, once you have sent the expected response. You 
should be able to test now with either the python peer, or with a second C 
peer with either being able to connect to the other. As it is within the 
Python peer, it will refuse a registration request from someone who has 
already registered, but you do not have to use the same logic within your own. 
Perhaps you find it more helpful to provide the response that although the 
user already exists and will not be registered again, you still provide a 
complete network list. That may make your system more robust to peers joining 
repeatedly though is not an essential thing to implement. 

Each peer should be able to handling multiple requests at the same time. This might be hard to manually test without inserting some delays into your system, such as _sleep(60)_ to slow each handling down by a minute (you may wish to delay for even longer). 
