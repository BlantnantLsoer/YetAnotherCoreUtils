this implementation of echo has feature parity* with the gnu coreutils version



*the only slight variations is a bug in the \c escape sequence which i don't wanna fix and a small implementation difference between GNU's -E and my -E option argument. 

in the traditional echo program, if -e is present even when there is any amount of -E arguments, escape sequences are always interpreted. in my implementation, if there are a varying amount of -e and -E
arguments, whether escape sequences are interpreted or not is determined by the last -e or -E argument. could i fix it? maybe. do i wanna spend hours trying to figure out why it's being this way? no. echo
isn't even portable if you look at the POSIX specification anyway.
