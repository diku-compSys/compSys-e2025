# Informing, Concurrency Controls and Error Handling
This exercise will continue our guidance through the A3 assignment. It 
presupposes that you have completed the subtasks described in the previous
exercises. You will also need to consult the handout for A3 for technical 
descriptions of the protocol and system as a whole.

Note, you do not need to follow this guide if you have your own ideas about 
how to solve A3. Additionally, this is not intended as a complete guide to 
every line you will need to write. It will describe much of the general 
structure and provide some specific functions as assistance, but you will need
to flesh out the bones provided here.

Finally, do note that not all of the tasks described in these guides are 
equal. Some will take considerably longer than others and so if you finish 
these all very quickly feel free to move on to the next ahead of time. 

## Sending an Inform Message
In the last set of exercises when handling a registration request we did not 
include informing all previously existing peers on the network of the new 
peer. Let us do so now. Assuming we've set up or previous implementation 
sensibly then this could be a very quick implementation. All we need to do is 
loop through the entire _network_ global variable and send a simple message 
with the newly added peer. It would make sense to do this alongside our 
registration handling. Note we should avoid sending an inform message either 
to ourselves, or to the actual registering peer as they both presumably 
already know about the registering peer.

Something additional to consider at this point is your logic for sending a 
request to another peer. Have you assumed you are always getting a response? 
The inform message does not expect a response, so if so be sure to discount it 
from the response waiting. If you are not always waiting for a response then 
you should be making sure that you do wait in the case of any other request 
messages.

Testing this may be quite complex. You will probably need at least 3 peers, 
and they should probably print the contents of their _network_ after each 
update to it. Consider if you have 3 peers, A, B and C. If you start A then 
connect B each should be able to eventually print that the complete network is 
A and B. If you then connect C to A, then you would also hope that all three 
can eventually print that the complete network is A, B and C. This will only 
happen if A sends an inform message to B about C.

## Handling an Inform Message
Similarly, handling the inform message should also be relatively quick to 
implement, at least initially. This could probably be a very similar function 
to how you handle the actual registration request only with no response being 
generated. Simple parse the message contents and update the _network_ variable 
as appropriate, making sure not to add the peer if it is already in the 
network.

Now it hopefully hasn't escaped your notice that we have numerous points in 
our code already where we are modify the global _network_ variable. This is a 
recipe for a race condition. You might not have noticed this from your testing 
as in practice it would be very hard to send things at exactly the right time 
to actually cause this race condition, but it does exist as a possibility, and 
so we must handle it. Also note that how severe this problem actually is, and 
if it is only present on the _network_ variable is dependent on your 
implementation. You may have more global variables and will need to manage 
them appropriately as well.

If you are not convinced of how this race condition could occur you should 
consider a much larger set of peers than you have probably been testing with, 
and over an actual network rather than just testing locally on your machine. 
Actual networking is considerably slower than local messages, which means 
there will be a significantly larger delay between sending a request and 
receiving a response. Consider if two new peers join at the same time, both 
will generate inform messages at the same time, which may both be received at 
the same time by another peer. Each of these inform messages would be handled 
on their own thread and could each be accessing the _network_.

There are a few different approaches we could use to manage our access to 
shared variables, but the most obvious here is probably to introduce a mutex. 
You may even need more than one lock, depending on your implementation. You 
should surround every interaction with the _network_ with a lock to ensure 
that correctness is maintained. Consider if the code you have written is still 
suitable. Do you need to rework any logic to ensure the minimum amount of code 
is within a lock? The more you can minimise lock usage, the more parallelism 
you are ensuring in your system. Also make sure that if you grab a lock, you 
ALWAYS release it at some point. You must not carelessly encounter any errors 
or return from a function without releasing it.

## Sending Error Responses
Our final small task for today is introducing some error messages. Hopefully 
you've been validating your inputs within the request handling thread, and if 
something fails then an error response must be sent. It would probably be 
worth standardising the construction of error messages in a function. I also 
added a line that will print error message as well to help debugging, you 
might wish to add similar functionality.
