//Awesome coin ICO

pragma solidity >=0.7.0 <0.9.0;

contract awesomecoin_ico {
    uint public max_awesomecoins =  1000000;
    
    uint public usd_to_awc = 1000;
    
    uint public total_awc_bought = 0;
    
    mapping(address => uint) equity_awc;
    
    mapping(address => uint) equity_usd;
    
    modifier can_buy_awc(uint usdInvested) {
        require(usdInvested * usd_to_awc + total_awc_bought <= max_awesomecoins);
        _;
    }
    
    function equity_in_awc(address investor) external view returns (uint) {
        return equity_awc[investor];
    }
    
    function equity_in_usd(address investor) external view returns (uint) {
        return equity_usd[investor];
    }
    
    function buyAwc(address investor, uint usdInvested) external can_buy_awc (usdInvested) {
        uint awcBought = usdInvested * usd_to_awc;
        equity_awc[investor] += awcBought;
        equity_usd[investor] = equity_awc[investor] / usd_to_awc;
        total_awc_bought += awcBought;
    }
    
    function sellAwc(address investor, uint awcToSell) external {
        equity_awc[investor] -= awcToSell;
        equity_usd[investor] = equity_awc[investor] / usd_to_awc;
        total_awc_bought -= awcToSell;
    }
}