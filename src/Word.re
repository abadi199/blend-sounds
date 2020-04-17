open Sound;

let str = React.string;

let calculateWidth = (): int => {
  let innerWidth: int = [%bs.raw {|window.innerWidth|}];
  let wordsWidth = [%bs.raw
    {|
    Array
      .from(document.getElementsByClassName("sound"))
      .map(function(elem) { return elem.getBoundingClientRect().width; })
      .reduce(function(a,b) { return a + b; }, 0)
|}
  ];
  innerWidth - wordsWidth;
};

[@react.component]
let make = (~distance: int) => {
  let width = Js.Int.toString(calculateWidth() * distance / 100) ++ "px";

  <div className="word">
    <Sound alignment=Right />
    <span className="gap" style={ReactDOMRe.Style.make(~width, ())} />
    <Sound alignment=Left />
  </div>;
};