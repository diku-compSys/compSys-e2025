# Managing Small File Requests
This exercise will continue our guidance through the A3 assignment. It 
presupposes that you have completed the subtasks described in the previous
exercises. You will also need to consult the handout for A3 for technical descriptions of the protocol and system as a whole.

Note, you do not need to follow this guide if you have your own ideas about 
how to solve A3. Additionally, this is not intended as a complete guide to 
every line you will need to write. It will describe much of the general 
structure and provide some specific functions as assistance, but you will need
to flesh out the bones provided here.

Finally, do note that not all of the tasks described in these guides are 
equal. Some will take considerably longer than others and so if you finish 
these all very quickly feel free to move on to the next ahead of time. 

## Getting a Random Peer
Now that our implementation is capable of sending a register message to 
retrieve the network, it is worth implementing a function to retrieve a random 
peer from that network. This will be used any time that we want to retrieve a 
file, so we might not need it for a wee while, but we can achieve it now, and 
it's relatively simple. 

For this, all we need to do is randomly select a peer from our global 
_network_ variable. How you do this will depend on how you have set up your 
_network_, e.g. does it include your own address or not. If it does, you need 
to make sure that you do not return your own address. A quick any easy way of 
generating a random number in a certain range is:

    uint32_t number = rand() % max;

This will generate a random integer value greater than or equal to zero, and 
less than max. Be sure that you also have not re-introduced any race 
conditions that you hopefully solved in the last exercise.

# Sending a File Request
It's finally time to start looking at actually retrieving some files. The 
starting point here is probably to modify the _client_thread_ function, to 
introduce a point where we ask the user for the name of a file to attempt to 
retrieve. In order to get the user input you can probably use the same logic 
as how we've retrieved the _peer_ip_ and _peer_port_ variables. Once you have 
a filename to retrieve then we can select a random peer as previously 
implemented and just need to assemble a message, which we've hopefully already 
started implementing in a _send_message_ function way back with the 
registration messages. Note that this whole interaction should take place 
within a loop, so that once we have completed this retrieval we start again.

We could create a new function for sending a file request message, or could 
incorporate it into the existing function for sending a request message. 
Personally I would put them both together as they share so much logic, though 
it is of course up to you. Regardless of how you do it you will need to do a 
lot of the same logic as in initially sending the registration request. The 
header will need to be assembled in the same manner, though this time you will 
also need to make sure to include a message body. Even if you have not 
implemented this within your request generation function, you should have 
implemented very similar logic within the response function. Note that here 
we're still assuming that everything fits into a single message, so a file to 
test with could be the provided _tiny.txt_ 

At this point we should also implement handling the reply to our request. This 
should be fairly straight forward, creating a file with the same name as was 
requested, and filling it with the reply body. As we're assuming for now that 
the entire file fits into a single message we don't need to do anything fancy, 
just write that message body into the file. Do remember to keep doing regular 
validation, such as that the total hash still matches the data you've been 
given. This might have been covered by your previous implementations, or you 
might need to add it in again. 

# Handling a File Request
We should also implement the server side handling of a retrieve request. Note 
that here we should add a bit more validation, not just of the regular message 
content but also of the file we are retrieving. For instance, our peer should 
be able to serve any file under it within the file directory, but it shouldn't 
serve anything above it. This is a good security principle to stick to as it 
prevents a peer just spuriously requesting any file on our system, some of 
which are presumably private. Doing this robustly can be quite an involved 
process but a good first step is to remove any leading '/' characters. This 
should ensure that any paths are at least relational to the peers working 
directory. 

    memmove(request, request+1, strlen(request))

A line such as the one above will remove the first character from a string 
while maintaining the pointer to that string at the same location. Of course 
you should make sure to only do so if necessary. Another helpful function 
could be this:

    fseek(fp, 0L, SEEK_END);
    int file_size = ftell(fp);

This will move the file position indicator to the end of the file pointed to 
by _fp_, and will then read that position into the _file_size_ variable. The 
name might be a hint here, but this will then give us the total length of that 
file, which presumably will also be the length of the message body. 

Once this and the previous task have been completed you should be able to 
fully retrieve small files. Make sure to test with the _diff_ command to check 
that your retrieved file contents are indeed the same as the original. 
