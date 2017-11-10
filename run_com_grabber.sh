#to be able read from /dev/ttyUSB0 you should be a member of the group uucp
#or other group, who owns /dev/ttyUSB, which can be inquired with
#ls -la /dev/ttyUSB0
#and add yourself to the group by typing
#sudo usermod -a G uucp my_user
./com_grabber -p16 -b1000000 -s1024 -m8N1 -l1 -w500 -a0
