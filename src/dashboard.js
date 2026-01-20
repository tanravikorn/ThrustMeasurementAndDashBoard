import { io } from "socket.io-client";
import Chart from 'chart.js/auto';


const SERVER_URL = "http://192.168.1.41:3000";
const MAX_DATA_POINTS = 100;

// ตัวแปรเก็บ instance ของกราฟ
let charts = {};

// 🟢 1. เพิ่มตัวแปรเช็คสถานะการอัดข้อมูล (เริ่มต้นเป็น false คือยังไม่พล็อต)
let isRecording = false; 

function createChart(ctx, label, color, unit) {
    return new Chart(ctx, {
        type: 'line',
        data: {
            labels: [],
            datasets: [{
                label: `${label} (${unit})`,
                data: [],
                borderColor: color,
                backgroundColor: color.replace('1)', '0.2)'),
                borderWidth: 2,
                tension: 0.3,
                fill: true,
                pointRadius: 0
            }]
        },
        options: {
            responsive: true,
            maintainAspectRatio: false,
            animation: false,
            scales: {
                x: { display: true, title: { display: true, text: 'Time' } },
                y: { beginAtZero: true }
            }
        }
    });
}

function updateChartData(chart, timestamp, value) {
    const timeLabel = new Date(timestamp).toLocaleTimeString();
    
    chart.data.labels.push(timeLabel);
    chart.data.datasets[0].data.push(value);

    if (chart.data.labels.length > MAX_DATA_POINTS) {
        chart.data.labels.shift();
        chart.data.datasets[0].data.shift();
    }
    chart.update();
}

function clearAllCharts() {
    Object.values(charts).forEach(chart => {
        chart.data.labels = [];
        chart.data.datasets[0].data = [];
        chart.update();
    });
}

export function initDashboard() {
    const slider = document.getElementById('throttleSlider');
    const sliderValue = document.getElementById('throttleValue');

    slider.addEventListener('input', (e) => {
        const val = e.target.value;
        sliderValue.innerText = val; // โชว์ตัวเลข
        
        socket.emit("control-throttle", val);
    });

    charts.thrust = createChart(document.getElementById('chartThrust'), 'Thrust', 'rgba(255, 99, 132, 1)', 'g');
    charts.voltage = createChart(document.getElementById('chartVoltage'), 'Voltage', 'rgba(54, 162, 235, 1)', 'V');
    charts.current = createChart(document.getElementById('chartCurrent'), 'Current', 'rgba(255, 206, 86, 1)', 'A');
    charts.power = createChart(document.getElementById('chartPower'), 'Power', 'rgba(75, 192, 192, 1)', 'W');


    const socket = io(SERVER_URL);

    const btnStart = document.getElementById('btnStart');
    const btnStop = document.getElementById('btnStop');
    const btnExport = document.getElementById('btnExport');
    const rpmLabel = document.getElementById('rpmValue');

    socket.on("connect", () => {
        console.log("Connected to Backend");
        socket.emit("get-history", (res) => {
            if (res.status === "ok") {
                res.data.forEach(d => {
                    updateChartData(charts.thrust, d.timestamp, d.thrust);
                    updateChartData(charts.voltage, d.timestamp, d.voltage);
                    updateChartData(charts.current, d.timestamp, d.current);
                    updateChartData(charts.power, d.timestamp, d.power);

                    if(rpmLabel) {
                        rpmLabel.innerText = d.rpm;
                    }
                });
            }
        });
    });

    //socket listen for new data record 
    socket.on("new-sensor-data", (data) => {
        if (!isRecording) return; 

        updateChartData(charts.thrust, data.timestamp, data.thrust);
        updateChartData(charts.voltage, data.timestamp, data.voltage);
        updateChartData(charts.current, data.timestamp, data.current);
        updateChartData(charts.power, data.timestamp, data.power);
    });

    //clear all graph 
    socket.on("clear-data", () => {
        clearAllCharts();
    });

    //start measure 
    btnStart.addEventListener('click', async () => {
        if(confirm("Start new measurement? This will clear old data.")){
            try {
                await fetch(`${SERVER_URL}/api/data/clear`, { method: 'DELETE' });

                socket.emit("control-command", "START");
                isRecording = true; 

                btnStart.innerText = "Running...";
                btnStop.innerText = "⏹ Stop";
                btnStart.disabled = true;
                btnStop.disabled = false;
                
            } catch (err) {
                console.error("Error starting:", err);
            }
        }
    });


    //stop measure 
    btnStop.addEventListener('click', () => {
        socket.emit("control-command", "STOP");
        isRecording = false;

        btnStart.innerText = "▶ Start Measurement";
        btnStop.innerText = "⏹ Stopped";
        btnStart.disabled = false;
        
        slider.value = 0;
        sliderValue.innerText = "0";
        socket.emit("control-throttle", 0);
        
        alert("Measurement Stopped (Graph frozen)");
    });

    //for export file csv form database 
    btnExport.addEventListener('click', () => {
        window.location.href = `${SERVER_URL}/api/data/export`;
    });
}