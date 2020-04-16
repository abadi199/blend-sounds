type state =
  | View(View.state);

type action =
  // | EditAction
  | ViewAction(View.action)
  | ViewClicked;

let str = React.string;

let toView = (state: state) => {
  switch (state) {
  | View(_) => state
  };
};

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) => {
        switch (action, state) {
        | (ViewAction(viewAction), View(viewState)) =>
          View(View.reducer(viewState, viewAction))
        | (ViewClicked, _) => toView(state)
        | _ => state
        }
      },
      View(View.initialState),
    );
  <div className="app">
    {switch (state) {
     | View(viewState) =>
       <View
         state=viewState
         dispatch={viewAction => dispatch(ViewAction(viewAction))}
       />
     }}
  </div>;
};