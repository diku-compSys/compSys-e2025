# Setting Up A3, Hashes and Salts
This exercise is designed to get you started with A3. You will need to consult
the actual A3 handout for a lot of technical description and the big picture
of how it all fits together. 

Note, you do not need to follow this guide if you have your own ideas about 
how to solve A3. Additionally, this is not intended as a complete guide to 
every line you will need to write. It will describe much of the general 
structure and provide some specific functions as assistance, but you will need
to flesh out the bones provided here. 

Finally, do note that not all of the tasks described in these guides are equal.
Some will take considerably longer than others and so if you finish these all 
very quickly feel free to move on to the next ahead of time. 

## Setting up 
In order to interact with anyone else in the eventual network, any peer needs 
to be given a user-remembered password, that is to be salted and hashed. This 
salted and hashed password will be referred to as the signature. It is 
intentionally ambiguous within the assignment text as to if a user should be 
prompted before every network request for the user remembered-password, or if 
we can just prompt once and be done with it. Prompting every time would be 
annoying to test on, so we can just adopt the strategy of asking as part of 
the peer startup. This has already been done for you in the handout, now we 
just need to apply the salt and hash it.

To store network addresses you have been provided the _NetworkAddress_ struct,
whose definition is viewable in peer.h. An instance of this has been set up as 
the _my_address_ variable so a peer can keep track of its own characteristics, 
and it is into here you should probably store the calculated signature. This 
signature calculation probably wants to be its own function, as we will have 
to perform this operation repeatedly throughout the final implementation.

Your signature function itself will need to take as inputs the user password, 
the salt to combine with said password, and probably a location as to where to
write the signature. Also note, that any time you are operating on strings, it 
can also be a good idea to take a parameter of exactly how long it is. I would
suggest a function signature such as:

    void get_signature(void* password, int password_len, char* salt, hashdata_t* hash)

You may not need all these parameters, or may need more depending on how you 
solve the problem. I've not passed a length for the salt or the final 
signature as these are always the same, and given by the _SALT_LEN_ and 
_SHA256_HASH_SIZE_ global variables.

Within that function I would then set up a buffer of the combined length of 
both the password and the salt, and then copy each of these in to form one big 
combined string. The final step is now to hash this combined string, for which 
we can use the provided _get_data_sha_ function. Note that this functions 
second parameter is the location that the hash is written, which is why I 
included the same pointer in my _get_signature_ signature above. I would 
therefore need to set up a hash location to write to before calling the 
_get_signature_ function. This could be done like so:

    hashdata_t* signature = (hashdata_t*)malloc(sizeof(hashdata_t));

Once we've set up the signature for the _my_address_ variable then it is 
complete. We should now decide on how we are saving our complete network, as 
I've suggested you do in the global _network_ variable. We then need to decide 
if this variable stores everyone in the network, including ourselves, or 
everyone excluding ourselves. Both are valid options, if you include yourself 
then you'll need to make sure not to pick your own address from the network 
when selecting a random peer, but if you don't add it you'll need to remember 
to add in your own address every time you're asked to report the whole network.

Either way, lets setup the _network_ variable now with a malloc. You can then 
either add _my_address_ as the first element and update the _peer_count_ (e.g. 
how many peers are recorded in the _network_)variable appropriately or not.

## Sending a first register message
The simplest message to assemble will probably be the first to be sent, that 
being the initial registration message. In order to test this you should start 
a python peer to connect to, as described in the assignment handout and README.
md. Depending on how much you've implemented or how robust your implementation 
is, you may need to restart the python peer between your connections, or you 
may not. You might want to start the python peer with the '-d' flag so that it 
will print out when it has received a message. Remember you can also add 
further debug messages or printing to the python as necessary.

Note that the client_thread when started in peer.c, already asks for an 
address to connect to. You now just need to create another function to send a 
message to said peer. I would suggest a function signature such as:

    void send_message(NetworkAddress_t peer_address, int command, char* request_body, int request_len)

Again, you may wish to use a different variety of attributes. Note that at the 
point that although we are using the _NetworkAddress_ struct to hold the IP 
and port of the _peer_address_, we do not yet know its password or salt and so 
they won't be populated, but hey, this just means we don't need to create 
another type of struct.

Within the send_message function we just need to set up a connection, 
including any relevant buffers or pointers. You should look to last weeks 
exercises for examples of how you open a client socket and initialise your 
buffers. 

One difficulty you may hit is that our _NetworkAddress_ is stored as an int, 
but the _compsys_helper_open_clientfd_ takes the port as a char. You can use 
the _sprintf_ to convert between integers and chars, but may need to look up 
how to use it correctly.

You now need to assemble the message header and body. The body is request body 
is easy as for this message type there is no body, and the header has a 
convenient struct _RequestHeader_ defined for it in peer.h. Create an instance 
of this struct and then populate each attribute in turn. Remember that 
according to the protocol, many of the numeric values are in network order, 
and so there will probably be many lines such as:

    request_header.command = htonl(command);

You don't need to convert any strings to different ordering so can simply copy 
those values into the header struct directly. Once your header struct is fully 
assembled you need to copy both the header and body to the buffer and call the 
_compsys_helper_writen_ function. Now although you don't have any body to write
in this message, it may be worth adding in support for it already, as pretty 
soon we'll be sending messages with bodies anyway.

## Handing the response to the register message
Once you can send a request, your peer should be capable of handling the 
response sent back to it. This may be in its own function, or as we always 
expect a reply, may be included as a second part of your message sending 
function.

Again, look to last weeks exercises on example of how you read messages. How 
much to read is set by the size of the reply header, which is given by the 
_REPLY_HEADER_LEN_ variable. We must only read the header first as we do not 
know how long the entire body is, but we can learn that from the header. 
Initially the header is just read into a buffer as a serise of bytes, so you 
must parse the different fields. For instance the first two being the length 
and the status could be read as:

    uint32_t reply_length = ntohl(*(uint32_t*)&reply_header[0]);
    uint32_t reply_status = ntohl(*(uint32_t*)&reply_header[4]);

These are reading one uint32 at a time, with the most important part to note 
being the final indexes of 0 and 4 at the end. These are essentially the 
position of these attributes within the total message. Note also we must 
convert from network to host order. 

Once you have all the header, we should then read the message body, whose 
length presumably matches the length told to us in the header. Remember at 
this point to perform some validation on the data you are reading. Is it 
sensible values that you expect to see, e.g. do we get a response status of 1 
e.g. OK? 

For now we can assume that any message we are receiving will fit into a single 
block, so perhaps avoid testing with 700 different peers. You should be able 
to get a complete network in a single message body, which you should read into 
a buffer. You can then take a hash of that message body using the 
_get_data_sha_ function and compare it against the hash given by the header. 
If those don't match then something's gone wrong, and you should report an 
error.

Assuming you've passed all your validation and read everything correctly, the 
final thing to do today is recording all of the network peers you have been 
told about. You can derive how many peers there are as the length of the body 
should divide neatly into some multiple of 68 bytes, that being the length of 
a single peer address. For each of there we need to allocate a new 
_NetworkAddress_ and copy the values from the message body. You will need to 
reallocate the global _network_ variable in order to store these new 
addresses, and update the _peer_count_ variable accordingly. Make sure not to 
add any addresses to your network that you already have.