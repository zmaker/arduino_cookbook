function doGet(e) {
  var par = e.parameter.dato;
  Logger.log(par);
  
  logToSpreadSheet(par);

  var ret = {status: 'success'};
  return ContentService.createTextOutput(JSON.stringify(ret)).setMimeType(ContentService.MimeType.JSON);
}


function logToSpreadSheet(value){
  var ss = SpreadsheetApp.openById('1wa5WQvOVNzkMFvrpGKXqmOqHA2LjR4fi-gp5h8Q51uE');
  var foglio = ss.getSheetByName('arduino');
  foglio.appendRow([new Date(), value]);
}