if [ -n "$__MY_IFS_SH__" ]; then
    return
fi
__MY_IFS_SH__='my_ifs.sh'

#source $cur_dir/my_stdio.sh

# get card ip 
function get_if_ip(){
	if [ $# -le 0 ];
	then
		my_echo "red" " Error:get_card_ip [card_name]  "
		return
	fi
	ifconfig $1 | grep -w inet | awk '{print $2}'
}

# get card mac 
function get_if_mac(){
	if [ $# -le 0 ];
	then
		my_echo "red" " Error:get_card_mac [card_name]  "
		return
	fi
	#ifconfig $1 | grep -w ether | awk '{print $2}'
	cat	"/sys/class/net/$1/address"
}

# get all network card names
function get_if_names(){
	ls /sys/class/net
}

# get all wireless card names
function get_wifi_names(){
	ls /sys/class/ieee80211/*/device/net/
}

# Choose interface
function pick_if(){
	# Get all wifi interface
	local all_ifs=$(get_if_names)
	local ifs_arr=($all_ifs)
	local len=$((${#ifs_arr[*]}-1))
	local i=0
	
	# Echo all interfaces
	my_printf "green" "null" "ID" "Interface" "IP" "MAC"
	for((i=0;i<=len;i++));
	do
		local card_ip=$(get_if_ip "${ifs_arr[i]}")
		local card_mac=$(get_if_mac "${ifs_arr[i]}")
		my_printf "null" "null" "$i" "${ifs_arr[i]}" "$card_ip" "$card_mac"
	done 
	
	# Chosing interface
	local in_id=""
	while [[ ! "$in_id" =~ ^[+-]?[0-9]+$ ]] || [ "$in_id" -lt 0 -o "$in_id" -gt "$len" ]; do
		my_echo "red" " please input 0~$len to choose the interface"
		read in_id
	done
	
	# Interface
	net_if=${ifs_arr[$in_id]}
	my_echo "red" " choosing interface:$net_if "
	
	eval "$1=$net_if"
	#return $net_if
}


# match route table
function rt_match(){
	local host_ip="$1"
	ip route list match $host_ip
	if [ $? -ne 0 ]; then
		my_echo "red" "\nHost $host_ip local route table match failed\n"
		route -n
	fi
}

# match arp table
function arpt_match(){
	local host_ip="$1"
	local out=$(ip neighbor show $host_ip)
	echo $out
	if [ -z "$out" ]; then
		my_echo "red" "\nHost $host_ip ARP table match failed\n"
		arp -n
	fi
}
