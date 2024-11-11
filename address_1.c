1)EMPLOYEE RECORDS


while true;
do
	echo -e "1.Insert the record \n2.Display the record \n3.Search the reecord \n4.Delete the reecord \n5 Modify the the record \n6.Exit"
	echo -e "\nEnter your choice :"
	read ch
	v=1
	case $ch in
		1)
			while [ $v -eq 1 ]
			do
				echo -e "Enter employee number:"
				read eno
				echo -e "Enter employee name:"
				read ename
				echo -e "Enter  mobile number:"
				read mobno
				echo -e "Enter city:"
				read city
				
				echo -e "$eno \t $ename \t  $mobno \t  $city ">>emp.txt
				echo -e "\nDo you want to continue? Press 1 to continue or 0 for exit"
				read v
			done 
				;;
		2)	
			cat emp.txt 
			;;
			
		3)
			echo -e "Enter employee name: "
			read ename
			grep $ename emp.txt ;;
		
		4) 
			echo -e "Enter employee name to delete:"
			read ename
			grep -v $ename emp.txt >> temp.txt 
			rm emp.txt
			mv temp.txt emp.txt
			;;
			
		5)
			echo -e "\nEnter the employee name you want to Modify: "
			read ename
			echo -e "\nEnter the new employee name: "
			read name
			
			sed -i s/$ename/$name/g emp.txt
			;;
		6)
			exit 
			;;
		*)
	esac
done
