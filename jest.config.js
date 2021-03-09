const { defaults } = require('jest-config');

module.exports = {
  ...defaults,
  transformIgnorePatterns: [],
  transform: {
    '^.+\\.jsx?$': 'babel-jest',
  },
};
