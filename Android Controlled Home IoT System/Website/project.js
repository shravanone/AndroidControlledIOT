class button{
    constructor(ID) {
        this.div = document.getElementById(ID);
        this.h1 = this.div.firstElementChild;
        this.h2 = this.h1.nextElementSibling;
        this.btn = this.div.lastElementChild;

        const onLoad = (response, x) => {
            if (x == "0") {
                this.on();
            }

            else {
                this.off();
            }
            this.h2.textContent = response;
            this.h1.textContent = parseInt(response) ? this.div.id + ' : On' : this.div.id + ' : Off';
        };
        this.onClick = () => {
            let x = this.h2.textContent;
            if (x == "0") {
                x = "1";
            }

            else {
                x = "0";
            }
            if(document.getElementById("currentspeed").textContent.charAt(document.getElementById("currentspeed").textContent.length-1)=="0"&&this.div.id.substring(0,3)=="Fan")
            {
                this.btn.textContent="Set Fan Speed";
                this.btn.classList.add('alert');

                setTimeout(()=>{
                    this.on();

                },1500);
            }
            else{
                var httpReq = new XMLHttpRequest();
                httpReq.onload = function () {
                    let response = this.responseText;
                    onLoad(response, x);
                };
                httpReq.open("GET", this.h1.id + ".php?bool=" + x, true);
                httpReq.send();
                var httpReq2 = new XMLHttpRequest();
                httpReq2.onload = function () {
                };
                httpReq2.open("GET", "index.php", true);
                httpReq2.send();
            }
        };

        this.fanOff = () => {
            var httpReq = new XMLHttpRequest();
            httpReq.onload = function () {
                let response = this.responseText;
                onLoad(response, "0");
            };
            httpReq.open("GET", this.h1.id + ".php?bool="+"0", true);
            httpReq.send();
            var httpReq2 = new XMLHttpRequest();
            httpReq2.onload = function () {
            };
            httpReq2.open("GET", "index.php", true);
            httpReq2.send();
        }

        this.off = () => {
            this.btn.textContent = "Turn Off";
            this.btn.classList.add('on');
            this.h1.textContent = this.div.id + " : On";
        };
        this.on = () => {
            this.btn.textContent = "Turn On";
            this.btn.classList.remove('on');
            if(this.btn.classList.contains('alert'))
            {
                this.btn.classList.remove('alert');
            }
            this.h1.textContent = this.div.id + " : Off";
        };

        if(this.h2.textContent=="1")
        {
            this.off();
        }
        else
        {
            this.on();  
        }        

        this.btn.addEventListener('click', this.onClick.bind());        
    }
}
class fanbutton{
    constructor(ID){
        this.fanbtn = document.getElementById(ID);
        const h1 = document.getElementById("currentspeed");
        this.onFanClick = () => {
            let y = this.fanbtn.textContent;
            var httpReq = new XMLHttpRequest();
            httpReq.onload = function () {
                h1.textContent = h1.textContent.substring(0,(h1.textContent.length)-1) + this.responseText;
                if(this.responseText=="0"&&fan1.h2.textContent!="0")
                {
                    fan1.fanOff();
                }
                else if(this.responseText!="0"&&fan1.btn.textContent=="Set Fan Speed"){
                    fan1.on();
                }
            };
            httpReq.open("GET", this.fanbtn.id.substring(0,((this.fanbtn.id.length)-1))+ ".php?fanspeed=" + y, true);
            httpReq.send();
            var httpReq2 = new XMLHttpRequest();
            httpReq2.onload = function () {
            };
            httpReq2.open("GET", "index.php", true);
            httpReq2.send();            
        }

        this.fanbtn.addEventListener('click',this.onFanClick.bind());

    }
}

class input{
    constructor(ID){
        this.div = document.querySelector(ID);
        const h1 = document.getElementById(ID);

        this.loadTemperature = () => {
            var httpReq2 = new XMLHttpRequest();
            httpReq2.onload = function () {
                if(this.responseText=="0")
                {
                    h1.textContent="Sensor Offline";    
                }
                else
                {
                    h1.textContent = "Current Temperature : "+this.responseText+" Degrees Centigrade";
                }
            };
            httpReq2.open("GET", "temp.php", true);
            httpReq2.send();                
        }

        this.loadTemperature();

        setInterval(() => {
            this.loadTemperature();
        }, 5000);
    }
}

class dropdown{
    constructor(ID){
        this.div = document.getElementById(ID);
        this.btn = this.div.children.item(1);
        this.ul = this.div.children.item(2);

        this.btn.addEventListener('mouseover',() => this.ul.classList.toggle('active'));
    }
}

const light1 = new button("Light 1");
const light2 = new button("Light 2");
const fan1 = new button("Fan 1");
const light3 = new button("Light 3");
const dropdown1 = new dropdown("dropdown");
const fanbtn0 = new fanbutton("fanspeed0");
const fanbtn1 = new fanbutton("fanspeed1"); 
const fanbtn2 = new fanbutton("fanspeed2"); 
const fanbtn3 = new fanbutton("fanspeed3"); 
const fanbtn4 = new fanbutton("fanspeed4"); 
const fanbtn5 = new fanbutton("fanspeed5"); 
const inputtemp = new input("input");

// setTimeout(function(){
//     document.getElementsByTagName('A')[0].style.display="none";
// },1);