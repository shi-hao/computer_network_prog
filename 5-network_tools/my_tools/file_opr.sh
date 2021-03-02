source ./my_function.sh

# Chose config items
function chose_cnf(){
	# Config file
	cnf_file=$1
	
	# Read ip mask gateway
	while read line
	do 
		arr=($line)
		ip_array+=(${arr[0]})
		mask_array+=(${arr[1]})
		gw_ip+=(${arr[2]})
		msg+=(${arr[3]})
	done <$cnf_file
	len=$((${#ip_array[*]}-1))
	
	# Echo all ip mask gw
	my_printf "green" "null" "ID" "IP" "MASK" "GW" "INFO" 
	for((i=0;i<=len;i++));
	do
		my_printf "null" "line" $i ${ip_array[i]}  ${mask_array[i]} ${gw_ip[i]} ${msg[i]}
	done 
	
	# Choosing config
	in_id=""
	while [[ ! "$in_id" =~ ^[0-9]+$ || $in_id -gt $len || $in_id -lt 0 ]]; do
		my_echo "red" " please input 0~$len to chose the ip config"
		read in_id
	done
	my_echo "red" " chosing IP:${ip_array[$in_id]} MASK:${mask_array[$in_id]} GW:${gw_ip[$in_id]} INFO:${msg[$in_id]}"
	
	# Var--ip mask gateway
	eval "$2=${ip_array[$in_id]}"
	eval "$3=${mask_array[$in_id]}"
	eval "$4=${gw_ip[$in_id]}"
}
