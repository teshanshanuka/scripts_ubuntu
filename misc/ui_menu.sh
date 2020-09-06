#! /bin/bash

# Read https://en.wikibooks.org/wiki/Bash_Shell_Scripting/Whiptail
# Better complex example at https://gist.github.com/wafsek/b78cb3214787a605a28b

clear

while [ 1 ]
do
	CHOICE=$(
	whiptail --title "My selector menu" --menu "Make your choice" 16 100 9 \
		"1)" "Option 1"   \
		"2)" "Option 2"  \
		"3)" "End script"  3>&2 2>&1 1>&3	
	)

	case $CHOICE in
		"1)")   
			result="What did you expect?"
		;;
		"2)")   
			result="Nothing here either"
		;;
		"3)") 
            break
		;;
	esac
	whiptail --msgbox "$result" 20 78
done

# Yes no menu
if (whiptail --yesno "Do you want to exit?" --yes-button "Yes, I do" --no-button "No, but exit"  10 70); then
    echo "You selected Yes, exit status was $?."
else
    echo "You selected No, exit status was $?."
fi
