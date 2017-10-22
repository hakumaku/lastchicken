var data = {
	name: 'Yoshi'
}

Vue.component('greeting', {
	template: '<p>Hey there, I am {{ name }}!<button v-on:click="changeName">Change Name</button></p>',
	data: function() {
		/* New object */
		return {
			name: 'Yoshi'
		};
		/* Refering to the identical object */
		// return data;
	},
	methods: {
		changeName: function() {
			this.name = 'Mario';
		}
	}
});

new Vue({
	el: '#vue-app1',
});

new Vue({
	el: '#vue-app2',
});

new Vue({
	el: '#vue-app3',
	data: {
		output: 'Your favorite food'
	},
	methods: {
		readRefs: function() {
			console.log('All the refs inside this object: ', this.$refs);
			this.output = this.$refs.foo.value;
			console.log(this.$refs.bar.innerText);
		}
	}
});