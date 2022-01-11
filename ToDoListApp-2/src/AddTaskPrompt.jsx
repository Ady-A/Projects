import React, { useState } from 'react'
import './AddTaskPrompt.css'

const AddTaskPrompt = (props) => {

  const handleInput = (event) => {
    if (event.keyCode == 13){
      props.setTaskNameHolder(r => [...r, event.target.value])
      props.setCounter(props.counter + 1)
      props.setTaskCount(r => [...r, props.counter])
      props.setAdding(false)
    }
    props.setTaskName(event.target.keyCode)

  }

  return(
    <div className="addTaskprompt">
      <input type="text" placeholder="Add a task..." value={props.taskName} onKeyDown={handleInput}/>
    </div>
  )
}

export default AddTaskPrompt