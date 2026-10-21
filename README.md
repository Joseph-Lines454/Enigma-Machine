
# Enigma Machine

<img width="800" height="1022" alt="Enigma_Machine" src="https://github.com/user-attachments/assets/0c4ff7f1-013e-4482-abbc-a5b0178b3654" />


##Description

This project aims to replicate an enigma machine. Users are able to configure the plugboard, rotor order as well as rotor positions.
Users are also able to encrypt/decrypt messages once the configurations have been applied.
There are some differences compared to the real enigma machine. The real Enigma machine has a reflector once the electrical current gets to the end of the rotors.
This project sends the current back through the rotors which can result in a plaintext and encrypted letter being the same (which was not possible with the real machine).
A encrypt and decrypt button is implemented, this was not apart of the original.

C++ was used for the internals of the enigma machine's logic and SFML was used for the GUI.

## How to operate GUI

Click on the Setup GUI button. You will interact with a plugboard. Click on two of the ports and click create connection.
To delete a collection click on the connection and click delete connection. Click Next.
Once you have clicked on next, you will be presented with the rotors. Click on the small boxes underneath and type a number from 1 - 3 (to specify the order).
To set the individual rotors position, click on the rotor until the desired position/number is reached. Click Next.
Type the letter which you want to encrypt. A yellow light will show the encrypted letter.

To decrypt a message click on the encrypt button and follow the same process above.

## How to operate CMD

Click on the setup CMD button. You will interact with a plugboard. type the two letters you want to swap when prompted. When ready quit the plugboard section and move onto the rotor section.
When presented with the rotor section, you will be asked to select a number between 1,2 and 3. This will determine the rotor order. Next, you need to determine each rotors individual starting
position. Input a number between 1 and 26 to do so for each rotor. Now type the letter which you want to encrypt and the program will be able to do show the encrypted letter.
To decrypt a letter click the encrypt button and repeat the steps listed above.


##Setup

DLL files from the SFML bin folder need to be added to the x64 debug folder.

Copy all files from the Enigma_Machine\Enigma_Machine\SFML-3.0.0\bin folder.
Paste them into the Enigma_Machine\Enigma_Machine\Enigma_Machine\x64\Debug folder.


## Work still needing to be done

Currently to reset the machine, the user needs to restart the program. A reset machine button is currently in progress.
When trying to setup the machine after already setting it up a error is produced.
Plugboard letter highlighting is slightly buggy, this needs to be fixed.
