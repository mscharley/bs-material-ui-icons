const icons = require('@material-ui/icons');
const fs = require('fs');
const os = require('os');

const variants = ['Outlined', 'Rounded', 'TwoTone', 'Sharp'];

const groupedIcons = Object.keys(icons).reduce((acc, value) => {
  const variant = variants.find(v => value.endsWith(v));
  const iconName = variant
    ? value.substring(0, value.length - variant.length)
    : value;
  const variantName = variant ? variant : 'Filled';

  acc[iconName] = acc[iconName] || [];
  acc[iconName].push([value, variantName]);

  return acc;
}, {});

Object.keys(groupedIcons).map(icon => {
  const variants = groupedIcons[icon];

  const contents = variants.reduce(
    (c, [importName, moduleName]) => `${c}
module ${moduleName} = {
  [@bs.module "@material-ui/icons/${importName}"][@react.component]
  external make: (
    ~className: string=?,
    ~color: [@bs.string] [
        | [@bs.as "inherit"] \`Inherit
        | [@bs.as "primary"] \`Primary
        | [@bs.as "secondary"] \`Secondary
        | [@bs.as "action"] \`Action
        | [@bs.as "error"] \`Error
        | [@bs.as "disabled"] \`Disabled
      ]=?,
    ~fontSize: [@bs.string] [
        | [@bs.as "default"] \`Default
        | [@bs.as "inherit"] \`Inherit
        | [@bs.as "small"] \`Small
        | [@bs.as "large"] \`Large
      ]=?,
    ~nativeColor: string=?,
    ~style: ReactDOM.Style.t=?,
    ~titleAccess: string=?,
    ~viewBox: string=?,
  ) => React.element = "default";
};
`,
    '',
  );

  return fs.writeFileSync(`./src/icons/${icon}.re`, contents);
});
