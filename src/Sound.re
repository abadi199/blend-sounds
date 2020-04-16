type sound =
  | Sound(string);

let toString = (Sound(sound): sound): string => sound;

let fromString = (sound: string): sound => Sound(sound);

let str = React.string;

[@react.component]
let make = (~sound, ~onClick=() => ()) => {
  <div
    className="sound"
    onClick={_evt => onClick()}>
    {str(toString(sound))}
  </div>;
};