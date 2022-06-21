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
            equations: ref<Equation[]>([]),
            variables: ref<Variable[]>([]),
            // isError: ref(null), // edit or add error status(include: equation, variable)
            // isFilling: ref(false), // is prompt open(include: equation, variable)
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
        }
    }
})