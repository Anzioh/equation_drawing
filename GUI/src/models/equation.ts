export interface Equation {
  id: number
  color: string
  equation: string
  srcEquation: string
  x?: Array<number>
  y?: Array<number>
  tokenList: Array<string>
}
