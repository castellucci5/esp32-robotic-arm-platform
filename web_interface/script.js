function sendCmd(cmd) {
  fetch(cmd)
    .then(response => response.text())
    .then(text => {
      document.getElementById("status").innerText = text;
    })
    .catch(error => {
      document.getElementById("status").innerText = "Errore comando";
      console.log(error);
    });
}
