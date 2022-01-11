import React, { useState } from 'react';
import Task from './Task'
import AddTask from './AddTask'
import AddTaskPrompt from './AddTaskPrompt'
import './index.css'

function App() {
  const [addingMain, setAddingMain] = useState(false)
  const [mainPromptVal, setMainPromptVal] = useState('')
  const [taskCount, setTaskCount] = useState([])
  const [counter, setCounter] = useState(0)
  const [taskNameHolder, setTaskNameHolder] = useState([])
  
    return (
    <div className= "general">
    <div className = "app">
      
      {taskCount.map((num) => <Task taskNameHolder={taskNameHolder[num]} />)}
      
      {addingMain?<AddTaskPrompt setAdding={setAddingMain}setCounter={setCounter} counter={counter} taskName={mainPromptVal} setTaskName={setMainPromptVal} setTaskCount={setTaskCount} setTaskNameHolder={setTaskNameHolder}/>:null}

      <AddTask setTaskCount={setTaskCount} setAdding={setAddingMain} adding={addingMain}/>
    </div>
    </div>
  );
}

export default App;