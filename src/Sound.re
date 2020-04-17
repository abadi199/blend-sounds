type mode =
  | Text
  | Blank;

type alignment =
  | Left
  | Center
  | Right;

let alignmentToString = (alignment: alignment): string => {
  switch (alignment) {
  | Left => "left"
  | Center => "center"
  | Right => "right"
  };
};

type state = {
  sound: string,
  mode,
  edit: bool,
};

let initialState = alignment => {
  {
    mode: Text,
    edit: false,
    sound:
      if (alignment == Right) {
        "cl";
      } else {
        "ock";
      },
  };
};

let str = React.string;

type action =
  | BlankClicked
  | EditClicked
  | SaveClicked(string)
  | TextClicked;

let reducer = (state, action) => {
  switch (action) {
  | BlankClicked => {...state, mode: Blank}
  | EditClicked => {...state, edit: true}
  | SaveClicked(sound) => {...state, edit: false, sound}
  | TextClicked => {...state, mode: Text}
  };
};

module ViewText = {
  [@react.component]
  let make = (~state) => {
    <>
      <span className="text"> {str(state.sound)} </span>
      {if (state.mode == Blank) {
         <span className="blank"> <canvas /> <span className="line" /> </span>;
       } else {
         str("");
       }}
    </>;
  };
};

module ModeButton = {
  [@react.component]
  let make = (~state, ~dispatch) => {
    switch (state.mode) {
    | Text =>
      <button
        className="transparent-button blank-button"
        title="Blank"
        onClick={_evt => dispatch(BlankClicked)}
      />
    | Blank =>
      <button
        className="transparent-button text-button"
        title="Blank"
        onClick={_evt => dispatch(TextClicked)}
      />
    };
  };
};

module EditButton = {
  [@react.component]
  let make = (~state, ~dispatch, ~value) =>
    if (state.edit) {
      <button
        className="transparent-button save-button"
        title="Edit"
        onClick={_evt => dispatch(SaveClicked(value))}
      />;
    } else {
      <button
        className="transparent-button edit-button"
        title="Edit"
        onClick={_evt => dispatch(EditClicked)}
      />;
    };
};

module EditText = {
  [@react.component]
  let make = (~value, ~setValue) => {
    <input
      className="sound-input"
      type_="text"
      value
      onChange={_evt => {
        let newValue: string = ReactEvent.Form.target(_evt)##value;
        setValue(_ => newValue);
      }}
    />;
  };
};

[@react.component]
let make = (~alignment, ~state, ~dispatch) => {
  let (value, setValue) = React.useState(_ => state.sound);
  <div className={"sound " ++ alignmentToString(alignment)}>
    {if (state.edit) {
       <EditText value setValue />;
     } else {
       <ViewText state />;
     }}
    <div className="action">
      <ModeButton state dispatch />
      <EditButton state dispatch value />
    </div>
  </div>;
};