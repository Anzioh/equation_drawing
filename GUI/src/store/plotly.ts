import { defineStore } from 'pinia'
import { ref } from 'vue'
import { Equation } from "@/models/equation";
import { Variable } from "@/models/variable";

export const usePlotlyStore = defineStore("plotly", {
    state:() => {
        return {
            plotly: ref(null),
            plotlyDOM: ref(null),
            plotlyData: ref([{}]),
            plotlyLayout: ref({
                autosize: true,
                margin: {l: 50, r: 0, b: 100, t: 0, pad: 0},
                showlegend: true,
                legend: {
                    x: 1,
                    y: 0.5
                },
                xaxis: {
                    title: "x axis",
                    autorange: false,
                    range: [-5, 5]
                },
                yaxis: {
                    title: "y axis",
                    autorange: false,
                    range: [-5, 5]
                },
                dragmode: 'pan',
                scrollZoom: true,
            }),
            plotlyOption: ref({
                dragmode: 'pan',
                scrollZoom: true,
                displayModeBar: true,
                displaylogo: false,
                modeBarButtonsToRemove: [
                    "sendDataToCloud",
                    "toImage"
                ],
                responsive: true
            }),
            plotlyRange: {
                x: {
                    start: -5,
                    end: 5
                },
                y: {
                    start: -5,
                    end: 5
                }
            },
            dpi: 800,
            equations: ref<Equation[]>([]),
            variables: ref<Variable[]>([])
        }
    },
    getters: {

    },
    actions: {
        draw():void {
            console.log(this.plotly, "plotly");
        },
        getRandomColor(): string {
            return '#' + Math.floor(Math.random() * 16777215).toString(16);
        },
        // get equation info by id
        getEquationMain(id: number) {
            let result:any = false;
            this.equations.forEach(item => {
                if (item.id == id) {
                    result = item;
                }
            })
            return result;
        },
        // get equation index by id
        getEquationIndex(id: number): number {
            let result: number = -1;
            this.equations.forEach((e, index) => {
                if (e.id == id) {
                    result = index;
                    return index;
                }
            })
            return result;
        }
    }
})