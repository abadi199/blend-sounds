type mode =
  | Text
  | Blank
  | Edit;

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
};

let initialState = alignment => {
  {
    mode: Text,
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
  | TextClicked;

let reducer = (state, action) => {
  switch (action) {
  | BlankClicked => {...state, mode: Blank}
  | EditClicked => {...state, mode: Edit}
  | TextClicked => {...state, mode: Text}
  };
};

[@react.component]
let make = (~alignment, ~state, ~dispatch) => {
  <div className={"sound " ++ alignmentToString(alignment)}>
    <span className="text"> {str(state.sound)} </span>
    {if (state.mode == Blank) {
       <span className="blank"> <canvas /> <span className="line" /> </span>;
     } else {
       str("");
     }}
    <div className="action">
      {switch (state.mode) {
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
       | Edit => str("")
       }}
      <button
        className="transparent-button edit-button"
        title="Edit"
        onClick={_evt => dispatch(EditClicked)}
      />
    </div>
  </div>;
};