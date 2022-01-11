import React, { useState } from 'react'
import './Task.css'
import SubWrapper from './SubWrapper'

const Task = (props) => {

    const [switcher, setSwitcher] = useState()

    const [subTracker, setSubTracker] = useState([])
    const [counterSub, setCounterSub] = useState(0)
    const [subTasks, setSubTasks] = useState([])
    const [subPromptVal, setSubPromptVal] = useState('')
    const [checkList, setCheckList] = useState([])
    const [circleState, setCircleState] = useState('Red')

    const taskActivate = (event) => {
        event.target.clicked = !event.target.clicked
        setSwitcher(event.target.clicked)
    }

    const circleStyle = {
      color: circleState,
    }

    return(
        <div>
            <div className="main-task" clicked={false} onClick={taskActivate}><i className="fas fa-circle" style={circleStyle}></i> {props.taskNameHolder} ▼</div>
            
            {switcher?<SubWrapper subTracker={subTracker}setSubTracker={setSubTracker} counterSub={counterSub} setCounterSub={setCounterSub} subPromptVal={subPromptVal} setSubPromptVal={setSubPromptVal} setSubTasks={setSubTasks} subTasks={subTasks} checkList={checkList} setCheckList={setCheckList} setCircleState={setCircleState}/>:null}
        </div>
    )
}

export default Task