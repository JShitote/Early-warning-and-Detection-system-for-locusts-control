<template>
  <div id="devicecard">
  <b-card>
    <b-card-text>Langata hospital</b-card-text>
    <b-tabs content-class="mt-3">
    <b-tab title="metrics" active>
    
    <Metrics></Metrics>
    
    </b-tab>
    <b-tab title="trend"><p>I'm the second tab</p></b-tab>
  </b-tabs>
  </b-card>
  
  </div>
</template>

<script>
import Metrics from "@/components/Metrics.vue";

export default {

components:{
  Metrics
}
  

}
</script>

<style scoped>

#devicecard {
width: 501px;
height: 509px;
/* border: 1px solid red */
margin-left:20px;

}
.card-text {
  font-size:21.034px;
  font-style: normal;
  text-align: left;
}

</style>