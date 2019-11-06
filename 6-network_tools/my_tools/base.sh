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
function my_echo(){
	if [ $# -le 1 ];
	then
		echo -e "\033[31m Error:my_echo [color] [info] \033[0m"
		return
	fi

	declare -A color_list
	color_list=(["red"]="31" ["green"]="32" ["blue"]="34")
	
	code=${color_list[$1]}
	echo -e "\033[${code}m$2 \033[0m"
} 

# printf function 
function my_printf(){
	if [ $# -le 2 ];
	then
		echo -e "\033[31m Error:my_printf [color] [line/null] [info1] [info2] ...\033[0m"
		return
	fi

	declare -A color_list
	color_list=(["default"]="" ["red"]="31" ["green"]="32" ["yellow"]="33" ["blue"]="34")
	code1=${color_list[$1]}

	declare -A shape
	shape=(["line"]=";4")
	code2=${shape[$2]}
	echo $code2

	for((i=3;i<=$#;i++));
	do
		eval tmp=\$$i
		printf "\033[${code1}${code2}m%-10s\033[0m" "$tmp"
	done
}