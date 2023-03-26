import React from "react";
import ReactDOM from "react-dom";
import GridZoom from './GridZoom';

const App = () => {
  return (
    <div style={{ width: '100vw', height: '100vh' }}>
      <GridZoom />
    </div>
  );
};

export default App;

ReactDOM.render(<App />, document.getElementById("root"));