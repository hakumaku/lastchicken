new Vue({
	el: '#vue-app1',
	data: {
		name: 'Kim',
		job: 'programmer',
		website: 'https://www.google.com',
		websiteTag: '<a href="https://www.google.com">Google</a>'
	},
	methods: {
		greet: function(string) {
			return 'Hello, world!!' + string;
		},
		getName: function() {
			return this.name + '(' + this.job + ')';
		}
	}
});

new Vue({
	el: '#vue-app2',
	data: {
		age: 25,
		x: 0,
		y: 0,
		newX: 0,
		newY: 0
	},
	methods: {
		increment: function() {
			this.age++;
		},
		decrement: function() {
			this.age--;
		},
		dbinc: function(inc) {
			this.age += inc;
		},
		dbdec: function(dec) {
			this.age -= dec;
		},
		updateXY: function(e) {
			this.x = e.offsetX;
			this.y = e.offsetY;
		},
		updateNewXY: function(e) {
			this.newX = e.offsetX;
			this.newY = e.offsetY;
		},
		click: function(e) {
			e.preventDefault();
			alert('You clicked me?!');
		}
	}
});

new Vue({
	el: '#vue-app3',
	data: {
		name: '',
		age: ''
	}
});

new Vue({
	el: '#vue-app4',
	data: {
		test1: 20,
		test2: 20,
		a: 0,
		b: 0,
		c: 0,
		d: 0
	},
	/* Runs whenever properties have been changed. */
	methods: {
		addToA: function() {
			console.log('addToA');
			return this.a + this.test1;
		},
		addToB: function() {
			console.log('addToB');
			return this.b + this.test1;
		}
	},
	/* Runs whenever the specific property has been changed. */
	computed: {
		addToC: function() {
			console.log('addToC');
			return this.c + this.test2;
		},
		addToD: function() {
			console.log('addToD');
			return this.d + this.test2;
		}
	}
});

new Vue({
	el: '#vue-app5',
	data: {
		available: false,
		nearby: false,
		red: true,
		blue: true
	},
	computed: {
		compClasses: function() {
			return {
				red: this.red,
				blue: this.blue
			};
		}
	}
});

new Vue({
	el: '#vue-app6',
	data: {
		error: true,
		success: true
	}
});

new Vue({
	el: '#vue-app7',
	data: {
		characters: ['Mario', 'Luigi', 'Yoshi', 'Bowser'],
		ninjas: [
			{name: 'Ryu', age: 25},
			{name: 'Yoshi', age: 35},
			{name: 'Ken', age: 55},
		]
	}
});