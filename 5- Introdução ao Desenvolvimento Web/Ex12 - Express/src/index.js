const express = require('express');

const app = express();
const PORT = 5000;

app.get('/', (request, response) => {
  response.send('Make your GET | PUT | DELETE requests');
});

app.use(express.json());
app.use(express.urlencoded({ extended: false }));

app.use('/store', require('./routes/store'));

app.use(express.static('public')).listen(PORT);
