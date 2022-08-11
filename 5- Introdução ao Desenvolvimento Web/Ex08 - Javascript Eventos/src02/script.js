window.addEventListener('DOMContentLoaded', () => {
  const colors = ['brown', 'green', 'blue', 'purple', 'yellow'];
  const changedH1 = document.querySelector('#change-heading');
  const selected = document.querySelector('.selected');
  const newDiv = document.createElement('div');
  newDiv.className = 'random';

  document.querySelectorAll('div').forEach((div) => {
    div.addEventListener(
      'mouseover',
      (e) => (selected.innerText = div.className + '!')
    );
    div.addEventListener('mouseleave', (e) => (selected.innerText = 'None!'));
  });

  changedH1.innerText = 'Hello World!';
  document.body.appendChild(newDiv);

  setInterval(() => {
    newDiv.className = colors[parseInt(Math.random() * colors.length)];
  }, 500);
});
