const express = require('express');
const router = express.Router();
let users = require('../db/users');

router.get('/:userName', (request, response) => {
  const [targetUser] = users.filter(
    (user) => user.name === request.params.userName
  );
  if (targetUser !== undefined) {
    response.json(targetUser);
  } else {
    response.status(400).json({
      error: `Bad request: user with name ${request.params.userName} not found!`,
    });
  }
});

router.get('/', (request, response) => {
  response.status(400).json({
    error: `Bad request: the user name must be specified!`,
  });
});

router.post('/', (request, response) => {
  const newUser = {
    name: request.body.name,
    email: request.body.email,
    password: request.body.password,
    address: request.body.address,
  };
  if (!(newUser.name && newUser.email && newUser.password && newUser.address)) {
    console.log(request.body);
    response.status(400).json({
      error:
        'Bad request: you must pass an object containing a "name", an "email", a "password" and an "address" to post an user!',
    });
  } else {
    if (users.filter((user) => user.name === newUser.name).length === 0) {
      users.push(newUser);
      response.json(newUser);
    } else {
      response.status(400).json({
        error: 'Bad request: This user already exists!',
      });
    }
  }
});

router.put('/:userName', (request, response) => {
  const [targetUser] = users.filter(
    (user) => user.name === request.params.userName
  );
  if (targetUser !== undefined) {
    if (request.body.name) targetUser.name = request.body.name;
    if (request.body.email) targetUser.email = request.body.email;
    if (request.body.password) targetUser.password = request.body.password;
    if (request.body.address) targetUser.address = request.body.address;
    response.json(targetUser);
  } else {
    response.status(400).json({
      error: `Bad request: user with name ${request.params.userName} not found!`,
    });
  }
});

router.delete('/:userName', (request, response) => {
  const [targetUser] = users.filter(
    (user) => user.name === request.params.userName
  );
  if (targetUser !== undefined) {
    users = users.filter((user) => user.name !== targetUser.name);
    response.json(targetUser);
  } else {
    response.status(400).json({
      error: `Bad request: user with name ${request.params.userName} not found!`,
    });
  }
});

module.exports = router;
