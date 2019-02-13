# Reason bindings for Material-UI-Icons

[![npm](https://img.shields.io/npm/v/@mscharley/bs-material-ui-icons.svg)](https://www.npmjs.com/package/@mscharley/bs-material-ui-icons) [![Greenkeeper badge](https://badges.greenkeeper.io/mscharley/bs-material-ui-icons.svg)](https://greenkeeper.io/)

[Reason](https://reasonml.github.io/) bindings for [material-ui-icons](https://github.com/callemall/material-ui).

## Status

🚧 This is a WIP, not everything is supported yet but we're getting close. 🚧

Feel free to create an issue or PR if you find anything missing.

## Installation

```
yarn add @mscharley/bs-material-ui-icons
yarn add @material-ui/core
yarn add @material-ui/icons
```

Then add `@mscharley/bs-material-ui-icons` to `bs-dependencies` in your `bsconfig.json`:

```json
{
  // ...
  "bs-dependencies": ["@mscharley/bs-material-ui-icons"]
}
```

## Usage

```reason
let component = ReasonReact.statelessComponent("Example");

let make = (_children) => {
  ...component,
  render: (_self) => <MscharleyBsMaterialUiIcons.Delete.Filled />
};
```

[You can find a list of available icons here.](https://material.io/tools/icons/) The icons are exposed as `<IconName.Theme />` from this library, which is slightly different to ReactJS which uses `<IconNameTheme />` or `<IconName />` for the filled theme.

## Help! The icon I want to use isn't available

Maybe this library hasn't been updated yet to include the new icon. No problems! You can easily use the same tooling we do to include any new icons you want with only a few lines of code.

```reason
module FancyNewIcon = MscharleyBsMaterialUiIcons.Icon.Make({
  [@bs.module "@material-ui/icons/FancyNewIcon"]
  external reactClass: ReasonReact.reactClass = "default";
});
```

Please also let us know that we're missing something in an issue! We'll get things updated as soon as possible.

## Design decisions

### Why does this module take so long to build?

There are an awful lot of icons available in `@material-ui/icons`; as of writing, around 5000 of them. Initially, this project exported all of these icons from one module file. This was very fast to build! However due to interactions with the way the `bsb` builds files and the way it writes imports this led to very big deployment packages, even with tree shaking. Using a single icon caused builds to increase in size by 3MB (~7x in my small project!) because all the icons were always being included.

This module now exports each group of icons into it's own file. This leads to a slightly different usage pattern to ReactJS, namely `<Delete.Filled />` instead of `<Delete />` or `<Delete.Outlined />` instead of `<DeleteOutlined />`. This isn't that big a deal, really. It also lets packagers only include the icons you're using. Unfortunately, it means that the BSB build is a little bit longer.

## Gotchas

### Why can't I `include MscharleyBsMaterialUiIcons`?

> MscharleyBsMaterialUiIcons.js is compiled in script mode while its dependent is not

Related to the build question above, this package uses the `namespace` option in BuckleScript. This means that `MscharleyBsMaterialUiIcons` is purely synthetic and there isn't actually a script to include and re-export. Even if this did work it would be discouraged because you would end up at square one with code elimination as highlighted in the design decision above.

The current recommended way to alias this library is as follows:

```reason
/* Icons.re */
open MscharleyBsMaterialUiIcons;

module PowerSettingsNew = PowerSettingsNew.Filled;
module ReportProblem = ReportProblem.Filled;
module Help = Help.Outlined;
```
