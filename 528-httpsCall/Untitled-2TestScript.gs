function doGet() {
  var ret = {status: 'success', data: 123};
  return ContentService.createTextOutput(JSON.stringify(ret)).setMimeType(ContentService.MimeType.JSON);
}
