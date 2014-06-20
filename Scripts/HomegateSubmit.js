info.debug("HomegateSubmit.js started");
//info.debug(info.town_webID);
//info.debug(info.town_webValue);

//Set the values
document.getElementById('searchfilter:searchMaskPanel:city').value = info.town_webValue;
//info.debug("Submit.js started2");
document.getElementById('searchfilter:searchMaskPanel:roomsFrom').value = info.minRooms_webValue;
//info.debug("Submit.js started3");
document.getElementById('searchfilter:searchMaskPanel:rentTo').value = info.maxRent_webValue;
//info.debug("Submit.js started4");
//info.debug(document.getElementById(info.town_webID).value);
//info.debug("Submit.js started5");

//Submit the form
document.getElementById('searchfilter:searchMaskPanel:searchButton').click();
info.debug("Submit.js finished");

//document.getElementById("ctl00_ContentPlaceHolderApplication_ResultListUserControl_ResultListRepeater_ctl04_ProductListResultItem_PropertyDetailsLabel").firstChild.text
