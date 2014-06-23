info.debug("HomegateFetcher.js started");


var elems = document.getElementsByTagName('*');
var i;
for (i in elems) {
   var description;
   var address;
   var price;
   var htmlLink;

   var nodeType = elems[i].nodeType;
   var attr = elems[i].attributes;
   // Type 1 represents the 'element' node type.
   if (nodeType == 1 && elems[i].hasAttribute('onclick') && attr.length == 1)
   {

      // The code in this if clause is kind of hacky. After inspecting the order of the childe nodes on the homegate website, we hardcoded these values here.
      // It might not work anymore when the homegate guys change the structure of their website.

      var titleNode = elems[i].childNodes[5]
      //console.log(titleNode.className)
      description = titleNode.childNodes[1].childNodes[0].innerHTML
      console.log(description)

      htmlLink = titleNode.childNodes[1].childNodes[0].getAttribute("href")
      console.log(htmlLink)


      var streetNode = elems[i].childNodes[7]
      //console.log(streetNode.className)
      address = streetNode.childNodes[0].innerHTML
      console.log(address)

      var priceNode = elems[i].childNodes[11]
      price = priceNode.childNodes[2].childNodes[1].innerHTML
      console.log(price)

      info.foundResult(description,address,price,htmlLink)
   }
}


var elems = document.getElementsByTagName('*');
var i;
var hasNextPage = false;
for (i in elems)
{
   if((' ' + elems[i].className + ' ').indexOf(' ' + 'forward iconLink' + ' ')
         > -1)
   {
      elems[i].click()
      info.debug("HomegateFetcher.js - going to next page");
      hasNextPage = true;
      break;
   }
}


info.debug("HomegateFetcher.js stoped");



////info.debug("ComparisFetcher.js started");
////info.debug(document.getElementById(info.list_id).firstChild.text)

//var baseLink = 'http://www.homegate.ch'

//var elems = document.getElementsByTagName('*'), i;
//for (i in elems) {

//   var attr = elems[i].attributes;
//   if(elems[i].hasAttribute("onclick") )// && attr.length == 1)
//   {
//       console.log("Found an attribute")
//   }

//   if((' ' + elems[i].className + ' ').indexOf(' ' + 'box result-item' + ' ')
//         > -1) {


//      //      info.debug(elems[i].className);
//      var boxChilds =  elems[i].childNodes;
//      var htmlLink;
//      var description;
//      var address;
//      var price;

//      var j;
//      for(j in boxChilds)
//      {
//         if((' ' + boxChilds[j].className + ' ').indexOf(' ' + 'clickable-area' + ' ')
//               > -1)
//         {
//            var clickableAreaNode = boxChilds[j];
//            htmlLink = baseLink + boxChilds[j].getAttribute("href")
//            var a;
//            for(a in clickableAreaNode.childNodes)
//            {
//               //console.log("a.className: " +clickableAreaNode.childNodes[a].className)
//               if((' ' + clickableAreaNode.childNodes[a].className + ' ').indexOf(' ' + 'description-column' + ' ')
//                     > -1)
//               {
//                  var descriptionColumnNode = clickableAreaNode.childNodes[a];
//                  var b;
//                  var descriptionAlreadyFound = false;
//                  for(b in descriptionColumnNode.childNodes)
//                  {
//                     //console.log("b.className: " + b.className)
//                     if((' ' + descriptionColumnNode.childNodes[b].className + ' ').indexOf(' ' + 'single-line' + ' ')
//                           > -1)
//                     {
//                        if(descriptionAlreadyFound == false)
//                        {
//                           description = descriptionColumnNode.childNodes[b].innerHTML;
//                           descriptionAlreadyFound = true;
//                           continue;
//                        }
//                        else
//                        {
//                           address = descriptionColumnNode.childNodes[b].innerHTML;
//                           break;
//                        }
//                     }
//                  }

//                  for(b in descriptionColumnNode.childNodes)
//                  {
//                     //console.log("b.className: " + b.className)
//                     if((' ' + descriptionColumnNode.childNodes[b].className + ' ').indexOf(' ' + 'details-section' + ' ')
//                           > -1)
//                     {
//                        var detailSectionNode = descriptionColumnNode.childNodes[b];
//                        var c;
//                        for(c in detailSectionNode.childNodes)
//                        {
//                           if((' ' + detailSectionNode.childNodes[c].className + ' ').indexOf(' ' + 'text-right right' + ' ')
//                                 > -1)
//                           {
//                              var textRightNode = detailSectionNode.childNodes[c];
//                              var d;
//                              for(d in textRightNode.childNodes)
//                              {
//                                 if((' ' + textRightNode.childNodes[d].className + ' ').indexOf(' ' + 'price-element' + ' ')
//                                       > -1)
//                                 {
//                                    var priceElementNode = textRightNode.childNodes[d];
//                                    var e;
//                                    for(e in priceElementNode.childNodes)
//                                    {
//                                       if((' ' + priceElementNode.childNodes[e].className + ' ').indexOf(' ' + 'price' + ' ')
//                                             > -1)
//                                       {
//                                          price = priceElementNode.childNodes[e].innerHTML;
//                                          break;
//                                       }
//                                    }
//                                    break;
//                                 }
//                              }
//                              break;
//                           }
//                        }
//                        break;
//                     }
//                  }
//               }
//            }
//         }
//      }

//      console.log("Link: " + htmlLink)
//      console.log("Description: " + description)
//      console.log("Price: " + price)
//      console.log("Address: " + address)

////      info.debug("Description: " + description)
////      info.debug("Price: " + price)
////      info.debug("Link: " + htmlLink)
////      info.debug("Address: " + address)
////      info.debug("\n")

//      info.foundResult(description,address,price, htmlLink)

//   }
//}




////info.debug("Fetcher.js 2");
////info.storeLink(document.getElementById(info.title_id).firstChild.href)
////info.finished();
