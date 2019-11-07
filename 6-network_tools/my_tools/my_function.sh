# echo function 
function my_echo(){
	if [ $# -le 1 ];
	then
		echo -e "\033[31m Error:my_echo [color] [info] \033[0m"
		return
	fi

	declare -A color_list
	color_list=(["red"]="31" ["green"]="32" ["blue"]="34")
	
	code=${color_list[$1]}
	echo -e "\033[${code}m$2\033[0m"
} 

# printf function 
function my_printf(){
	if [ $# -le 2 ];
	then
		echo -e "\033[31m Error:my_printf [color/null] [line/null] [info1] [info2] \033[0m"
		return
	fi

	declare -A color_list
	color_list=( ["red"]="31" ["green"]="32" ["yellow"]="33" ["blue"]="34")
	code1=${color_list[$1]}

	declare -A shape
	shape=(["line"]=";4")
	code2=${shape[$2]}

	for((parm_num=3;parm_num<=$#;parm_num++));
	do
		eval parm=\$$parm_num
		printf "\033[${code1}${code2}m%-16s\033[0m" "$parm"
	done
	printf "\n"
}

# pause function
function pause(){
	while true
	do
		isContinue='y'
		my_echo "red" " 请输入y继续，输入n退出 [y/n] "
		read isContinue
		if [ "$isContinue" == "y" ]; then
			break
		elif [ "$isContinue" == "n" ]; then
			exit
		fi
	done
}

#get card ip 
function get_card_ip(){
	if [ $# -le 0 ];
	then
		echo -e "\033[31m Error:get_card_ip [card_name]  \033[0m"
		return
	fi
	ifconfig $1 | grep -w inet | awk '{print $2}'
}

#get card mac 
function get_card_mac(){
	if [ $# -le 0 ];
	then
		echo -e "\033[31m Error:get_card_mac [card_name]  \033[0m"
		return
	fi
	ifconfig $1 | grep -w ether | awk '{print $2}'
}
