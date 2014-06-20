info.debug("Fetcher.js a started");
//info.debug(document.getElementById(info.list_id).firstChild.text)

var elems = document.getElementsByTagName('*'), i;
for (i in elems) {
    if((' ' + elems[i].className + ' ').indexOf(' ' + 'box result-item' + ' ')
            > -1) {
      info.debug(elems[i].className);
      var node = elems[i].childNodes[3];

      var htmlLink = node.getAttribute("href")
      info.debug(htmlLink)
      var descColumn = node.childNodes[3];
//       info.debug(node.firstChild.className);
      var description = descColumn.childNodes[1].innerHTML;
      info.debug(description);
      // console.log(elems.size());
      var detailsSection = descColumn.childNodes[5];
      var price = detailsSection.childNodes[3].childNodes[3].childNodes[1];
      info.debug(price.innerHTML);

    }
}




//info.debug("Fetcher.js 2");
//info.storeLink(document.getElementById(info.title_id).firstChild.href)
//info.finished();
