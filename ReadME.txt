Name ; Adil Aman Mohammed
CWID : A20395630

The following are Instructions to Execute the program using csx1 server (csx1.cs.okstate.edu)

Open CMD in your system and Use the following command to connect to csx server through login "ssh user@csx1.cs.okstate.edu"

Step 1)log in to csx1 server

        Use Winscp to transfer your local file to server 

Step 2)Use the below Command to compile the file.c :
              gcc main.c funtions.c

Step 3)The following is the format to execute the code :   
          file name : 1.test.txt 2.gcc.txt 3.bzip.txt
          nframes : input for number of frames
          fifo|lru : 1.fifo 2.lru

        ./a.out <file number> <nframes> <fifo|lru>.    (this is the format of input)
        
        Use the below Command to run the code :
        
        ./a.out 1 3 1
