document.addEventListener('DOMContentLoaded', () => {
  function updateBodyStyle() {
    document.body.style.fontFamily = 'Courier';
    document.body.style.backgroundColor = 'darkBlue';
    document.body.style.color = 'white';
    document.body.style.listStylePosition = 'inside';
    document.body.style.height = '600px';
    document.body.style.display = 'flex';
    document.body.style.flexDirection = 'column';
    document.body.style.alignItems = 'center';
    document.body.style.justifyContent = 'space-evenly';
  }

  function changePageSubject(newSubject) {
    document.title = newSubject;
    document.querySelector('h1').innerText = newSubject;
  }

  function addPersonalInformation(name, nickname, favorites, hometown) {
    document.querySelector('#name').appendChild(document.createTextNode(name));
    document
      .querySelector('#nickname')
      .appendChild(document.createTextNode(nickname));
    document
      .querySelector('#favorites')
      .appendChild(document.createTextNode(favorites));
    document
      .querySelector('#hometown')
      .appendChild(document.createTextNode(hometown));
  }

  function addPersonalPhoto(src, alt) {
    const img = document.createElement('img');
    img.src = src;
    img.alt = alt;
    img.style.height = '300px';
    img.style.width = '350px';
    document.body.appendChild(img);
  }

  updateBodyStyle();
  changePageSubject('About me');
  addPersonalInformation(
    'Luiz Fernando',
    'Rabelo',
    '?',
    'São Sebastião do Paraíso - MG'
  );
  addPersonalPhoto('./me.jpg', 'Minha foto de perfil');
});
