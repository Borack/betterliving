//info.debug("Fetcher.js a started");
//info.debug(document.getElementById(info.list_id).firstChild.text)

var elems = document.getElementsByTagName('*'), i;
for (i in elems) {
    if((' ' + elems[i].className + ' ').indexOf(' ' + 'box result-item' + ' ')
            > -1) {

        var j;

        //      info.debug(elems[i].className);
        var boxChilds = elems[i].childNodes;
        var htmlLink;
        var description;
        var price;

        for(j in boxChilds)
        {
            if((' ' + boxChilds[j].className + ' ').indexOf(' ' + 'clickable-area' + ' ')
                    > -1)
            {
                var clickableAreaNode = boxChilds[j];
                htmlLink = boxChilds[j].getAttribute("href")
                var a;
                for(a in clickableAreaNode.childNodes)
                {
                    //console.log("a.className: " +clickableAreaNode.childNodes[a].className)
                    if((' ' + clickableAreaNode.childNodes[a].className + ' ').indexOf(' ' + 'description-column' + ' ')
                            > -1)
                    {
                        var descriptionColumnNode = clickableAreaNode.childNodes[a];
                        var b;
                        for(b in descriptionColumnNode.childNodes)
                        {
                            //console.log("b.className: " + b.className)
                            if((' ' + descriptionColumnNode.childNodes[b].className + ' ').indexOf(' ' + 'single-line' + ' ')
                                    > -1)
                            {
                                description = descriptionColumnNode.childNodes[b].innerHTML;
                                break;
                            }
                        }

                        for(b in descriptionColumnNode.childNodes)
                        {
                            //console.log("b.className: " + b.className)
                            if((' ' + descriptionColumnNode.childNodes[b].className + ' ').indexOf(' ' + 'details-section' + ' ')
                                    > -1)
                            {
                                var detailSectionNode = descriptionColumnNode.childNodes[b];
                                var c;
                                for(c in detailSectionNode.childNodes)
                                {
                                    if((' ' + detailSectionNode.childNodes[c].className + ' ').indexOf(' ' + 'text-right right' + ' ')
                                            > -1)
                                    {
                                        var textRightNode = detailSectionNode.childNodes[c];
                                        var d;
                                        for(d in textRightNode.childNodes)
                                        {
                                            if((' ' + textRightNode.childNodes[d].className + ' ').indexOf(' ' + 'price-element' + ' ')
                                                    > -1)
                                            {
                                                var priceElementNode = textRightNode.childNodes[d];
                                                var e;
                                                for(e in priceElementNode.childNodes)
                                                {
                                                    if((' ' + priceElementNode.childNodes[e].className + ' ').indexOf(' ' + 'price' + ' ')
                                                            > -1)
                                                    {
                                                        price = priceElementNode.childNodes[e].innerHTML;
                                                        break;
                                                    }
                                                }
                                                break;
                                            }
                                        }
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }

        console.log("Link: " + htmlLink)
        console.log("Description: " + description)
        console.log("Price: " + price)

        info.debug("Description: " + description)
        info.debug("Price: " + price)
        info.debug("Link: " + htmlLink)
        info.debug("\n")


        var node = elems[i].childNodes[3];

        //      info.debug(htmlLink)
        //      var descColumn = node.childNodes[3];
        //       info.debug(node.firstChild.className);
        //      var description = descColumn.childNodes[1].innerHTML;
        //      info.debug(description);
        //       console.log(elems.length);

        //      var detailsSection = descColumn.childNodes[5];
        //      var price = detailsSection.childNodes[3].childNodes[3].childNodes[1];
        //console.log("Price: " + price.innerHTML);

    }
}




//info.debug("Fetcher.js 2");
//info.storeLink(document.getElementById(info.title_id).firstChild.href)
//info.finished();
