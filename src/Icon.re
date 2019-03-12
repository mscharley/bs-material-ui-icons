open Belt.Option;

[@bs.deriving jsConverter]
type color = [
  | [@bs.as "default"] `Default
  | [@bs.as "error"] `Error
  | [@bs.as "inherit"] `Inherit
  | [@bs.as "primary"] `Primary
  | [@bs.as "secondary"] `Secondary
  | [@bs.as "textPrimary"] `TextPrimary
  | [@bs.as "textSecondary"] `TextSecondary
];

[@bs.deriving jsConverter]
type fontSize = [
  | [@bs.as "default"] `Default
  | [@bs.as "inherit"] `Inherit
  | [@bs.as "small"] `Small
  | [@bs.as "large"] `Large
];

[@bs.obj]
external makeProps:
  (
    ~className: string=?,
    ~color: string=?,
    ~fontSize: string=?,
    ~nativeColor: string=?,
    ~style: ReactDOMRe.Style.t=?,
    ~titleAccess: string=?,
    ~viewBox: string=?,
    unit
  ) =>
  _ =
  "";

module type IconClass = {let reactClass: ReasonReact.reactClass;};

module Make = (Icon: IconClass) => {
  include Icon;
  let make =
      (
        ~className: option(string)=?,
        ~color: option(color)=?,
        ~fontSize: option(fontSize)=?,
        ~nativeColor: option(string)=?,
        ~style: option(ReactDOMRe.Style.t)=?,
        ~titleAccess: option(string)=?,
        ~viewBox: option(string)=?,
        children: array(ReasonReact.reactElement),
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props=
        makeProps(
          ~className?,
          ~color=?color->map(colorToJs),
          ~fontSize=?fontSize->map(fontSizeToJs),
          ~nativeColor?,
          ~style?,
          ~titleAccess?,
          ~viewBox?,
          (),
        ),
      children,
    );
};
