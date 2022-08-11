const happinessInput = document.querySelector('#happiness-number');
const resultParagraph = document.querySelector('#joe-result');
const happyBtn = document.querySelector('#is-happy-btn');

//! A) Callback
// const getJoeHappiness = (happy, callback) => {
//   setTimeout(() => {
//     const happiness = Math.random();
//     if (happiness > happy) {
//       callback(happiness);
//     } else {
//       callback(new Error('Joe is sad!'));
//     }
//   }, 2000);
// };
// function result(happiness) {
//   if (isNaN(happiness)) {
//     resultParagraph.innerText = 'No! Joe is sad.';
//     resultParagraph.style.color = 'red';
//   } else {
//     happiness = happiness.toFixed(2);
//     resultParagraph.innerText = 'Yes! Joe is happy by ' + happiness * 100 + '%';
//     resultParagraph.style.color = 'green';
//   }
// }
// happyBtn.addEventListener('click', () => {
//   getJoeHappiness(Number(happinessInput.value), result);
// });

//! B) Promises
// const getJoeHappiness = (happy) => {
//   return new Promise((res, err) => {
//     setTimeout(() => {
//       const happiness = Math.random();
//       if (happiness > happy) {
//         res(happiness);
//       } else {
//         err(new Error('Joe is sad!'));
//       }
//     }, 2000);
//   });
// };
// happyBtn.addEventListener('click', () => {
//   getJoeHappiness(Number(happinessInput.value))
//     .then((happiness) => {
//       happiness = happiness.toFixed(2);
//       resultParagraph.innerText =
//         'Yes! Joe is happy by ' + happiness * 100 + '%';
//       resultParagraph.style.color = 'green';
//     })
//     .catch((err) => {
//       resultParagraph.innerText = 'No! Joe is sad.';
//       resultParagraph.style.color = 'red';
//       console.log(err);
//     });
// });

//! C) AsyncAwait
// const getJoeHappiness = (happy) => {
//   return new Promise((res, err) => {
//     setTimeout(() => {
//       const happiness = Math.random();
//       if (happiness > happy) {
//         res(happiness);
//       } else {
//         err(new Error('Joe is sad!'));
//       }
//     }, 2000);
//   });
// };
// happyBtn.addEventListener('click', async () => {
//   try {
//     let happiness = await getJoeHappiness(Number(happinessInput.value));
//     happiness = happiness.toFixed(2);
//     resultParagraph.innerText = 'Yes! Joe is happy by ' + happiness * 100 + '%';
//     resultParagraph.style.color = 'green';
//   } catch (err) {
//     resultParagraph.innerText = 'No! Joe is sad.';
//     resultParagraph.style.color = 'red';
//     console.log(err);
//   }
// });
