type mode =
  | Text
  | Blank;

type side =
  | Left
  | Center
  | Right;

let sideToString = (side): string => {
  switch (side) {
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

let initialState = side => {
  {
    mode: Text,
    edit: false,
    sound:
      if (side == Left) {
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
  let make = (~state, ~side) => {
    <>
      <span className="text"> {str(state.sound)} </span>
      {if (state.mode == Blank) {
         <span className="blank">
           <PenArea id={sideToString(side)} />
           <span className="line" />
         </span>;
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
let make = (~side, ~state, ~dispatch) => {
  let (value, setValue) = React.useState(_ => state.sound);
  <div className={"sound " ++ sideToString(side)}>
    {if (state.edit) {
       <EditText value setValue />;
     } else {
       <ViewText state side />;
     }}
    <div className="action">
      <ModeButton state dispatch />
      <EditButton state dispatch value />
    </div>
  </div>;
};