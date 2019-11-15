# echo function 
function my_echo(){
	if [ $# -le 1 ];
	then
		echo -e "\033[31m Error:my_echo [color] [info] \033[0m"
		return
	fi

	declare -A local color_list
	color_list=(["red"]="31" ["green"]="32" ["yellow"]="33" ["blue"]="34")
	
	local color=${color_list[$1]}
	echo -e "\033[${color}m$2\033[0m"
} 

# printf function 
function my_printf(){
	if [ $# -le 2 ];
	then
		echo -e "\033[31m Error:my_printf [color/null] [line/null] [info1] [info2] \033[0m"
		return
	fi

	declare -A local color_list
	color_list=( ["red"]="31" ["green"]="32" ["yellow"]="33" ["blue"]="34")
	local color=${color_list[$1]}

	declare -A local style_list
	style_list=(["line"]=";4")
	local style=${style_list[$2]}

	local i
	local parm
	for((i=3;i<=$#;i++));
	do
		eval parm=\$$i
		printf "\033[${color}${style}m%-16s\033[0m" "$parm"
	done
	printf "\n"
}

# pause function
function pause(){
	while true
	do
		local isContinue='y'
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
		my_echo "red" " Error:get_card_ip [card_name]  "
		return
	fi
	ifconfig $1 | grep -w inet | awk '{print $2}'
}

#get card mac 
function get_card_mac(){
	if [ $# -le 0 ];
	then
		my_echo "red" " Error:get_card_mac [card_name]  "
		return
	fi
	#ifconfig $1 | grep -w ether | awk '{print $2}'
	cat	"/sys/class/net/$1/address"
}

#get all network card names
function get_if_names(){
	ls /sys/class/net
}
