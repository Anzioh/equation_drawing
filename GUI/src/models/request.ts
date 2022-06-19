export interface Request{
    method: string;
    token: string;
    completed: boolean;
    result: any;
    callback: void;
}