# pause function
function pause(){
	while true
	do
		isContinue='y'
		echo -e "\033[31m 请输入y继续，输入n退出 [y/n] \033[0m"
		read isContinue
		if [ "$isContinue" == "y" ]; then
			break
		elif [ "$isContinue" == "n" ]; then
			exit
		fi
	done
}

# echo function
function echo_red(){
	echo -e "\033[31m$1 \033[0m"
}

# echo function
function echo_green(){
	echo -e "\033[32m$1 \033[0m"
}

# printf function
function printf_2_yell(){
	printf "\033[33m%-5s %-20s\n\033[0m" $1 $2 
} 

# printf function
function printf_2_default(){
	printf "%-5s %-20s\n" $1 $2 
}

# printf function
function printf_5_yell(){
	printf "\033[33m%-5s%-20s%-20s%-20s%-20s\n\033[0m" $1 $2 $3 $4 $5 
}

# printf function
function printf_5_under_line(){
	printf "\033[4m%-5s%-20s%-20s%-20s%-20s\n\033[0m" $1 $2 $3 $4 $5 
}
