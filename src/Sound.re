type sound =
  | Sound(string);

type alignment =
  | Left
  | Center
  | Right;

let toString = (Sound(sound): sound): string => sound;

let alignmentToString = (alignment: alignment): string => {
  switch (alignment) {
  | Left => "left"
  | Center => "center"
  | Right => "right"
  };
};

let fromString = (sound: string): sound => Sound(sound);

let str = React.string;

[@react.component]
let make = (~sound, ~alignment, ~onClick=() => ()) => {
  <div
    className={"sound " ++ alignmentToString(alignment)}
    onClick={_evt => onClick()}>
    {str(toString(sound))}
  </div>;
};