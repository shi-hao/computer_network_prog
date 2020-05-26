# open the monitor mode
如何利用 Wireshark 來監聽 IEEE 802.11 的管理封包 

因為工作的緣故，需要去監聽無線網路的封包，特別是IEEE802.11的管理控制訊框（
frame ... 其實我還是比較喜歡直接叫作封包）。同事直接打開 wireshark 卻擷取 wifi
介面，卻發現聽到了一堆 ethernet 的訊框而聽不到 wifi 的訊框。為什麼呢？來看看
wireshark 的官網怎麼說：



If you're trying to capture network traffic that's not being sent to or from
the machine running Wireshark or TShark, i.e. traffic between two or more
other machines on an Ethernet segment, or are interested in 802.11 management
or control packets, or are interested in radio-layer information about
packets, you will probably have to capture in "monitor mode". This is
discussed below.



Without any interaction, capturing on WLAN's may capture only user data
packets with "fake" Ethernet headers. In this case, you won't see any 802.11
management or control packets at all, and the 802.11 packet headers are
"translated" by the network driver to "fake" Ethernet packet headers.  



答案揭曉，原來這是因為 wifi driver 會自動把 wireless frame 轉成 ethernet frame
後再給 kernel，這樣 kernel 裏面的 protocol stack 會比較好處理。



問題是，如果我想要聽到 wifi frame 的話，要怎麼做呢？答案很簡單，將 wifi
adapter 設成 monitor mode。在 wifi adapter 中，通常都有 SSID/ESSID filter，所
以就算把 wifi adapter 設定成為 promiscuous mode 也沒有用，因為還是無法收到非自
己加入的 SSID 的 frame。那 monitor mode 呢？我們可以看看下面這句話：



In monitor mode the SSID filter mentioned above is disabled and all packets of
all SSID's from the currently selected channel are captured.



最後的問題就是，如何在 Linux 裏面把無線網卡設定成 monitor mode了。步驟如下：

1.iw dev wlan0 interface add mon0 type monitor

2.ifconfig mon0 up

接下來就可以透過 mon0 這虛擬介面來聽封包了。要移除這介面的方法也很簡單：

1.iw dev mon0 interface del 
