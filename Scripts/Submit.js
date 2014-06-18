info.debug("Submit.js started");
//info.debug(info.town_webID);
//info.debug(info.town_webValue);

//Set the values
document.getElementById(info.town_webID).value = info.town_webValue;
document.getElementById(info.maxRent_webID).value = info.maxRent_webValue;
document.getElementById(info.minRooms_webID).value = info.minRooms_webValue;	
//info.debug(document.getElementById(info.town_webID).value);

//Submit the form
document.getElementById(info.submit).click();
info.debug("Submit.js finished");

//document.getElementById("ctl00_ContentPlaceHolderApplication_ResultListUserControl_ResultListRepeater_ctl04_ProductListResultItem_PropertyDetailsLabel").firstChild.text