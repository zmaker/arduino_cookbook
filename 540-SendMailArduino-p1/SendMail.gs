function doGet(e) {
  var secret = e.parameter.secret;

  var address = "nomemail@gmail.com";
  var message = "Invio di prova da arduino";
  var subject = "Una mail da Arduino";

  var nmail = MailApp.getRemainingDailyQuota();
  var ret;

  if ((secret == 1234) && (nmail > 0)) {
    MailApp.sendEmail(address, subject, message);
    Logger.log("Inviata");
    ret = {status: 'success', msg: nmail};
  } else {
    ret = {status: 'failed', msg: 'ko'};
  }
  return ContentService.createTextOutput(JSON.stringify(ret)).setMimeType(ContentService.MimeType.JSON);
  
}
