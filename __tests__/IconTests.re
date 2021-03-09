open Jest;

module ReactTestRenderer = {
  // Borrowed from https://github.com/reasonml-community/bs-react-test-renderer
  // Inlined rather than used as a library as they haven't updated to @rescript/react
  type t;

  [@bs.module "react-test-renderer"] [@bs.val]
  external create: React.element => t = "create";

  [@bs.send] external toJSON: t => Js.Json.t = "toJSON";
};

describe("AccessTime", () => {
  ExpectJs.(
    test("snapshot", () => {
      let component =
        ReactTestRenderer.create(
          <AccessTime.Filled
            className="hello-world"
            color=`Primary
            fontSize=`Large
            nativeColor="#000000"
            style={ReactDOM.Style.make(~width="50px", ~height="50px", ())}
            titleAccess="access title"
            viewBox="viewbox"
          />,
        );

      expect(component |> ReactTestRenderer.toJSON) |> toMatchSnapshot;
    })
  )
});
