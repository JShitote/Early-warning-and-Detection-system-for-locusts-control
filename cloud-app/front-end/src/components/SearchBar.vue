<template>
<div>

<div id="searchbar">
  <b-input-group 
  label="Email address:"
  label-for="input-1" 
  class="mt-3 text-ex" >
    <template v-slot:append class="text-ex">
      <b-input-group-text ><strong>
      <b-icon-search></b-icon-search>
      </strong>
      </b-input-group-text>
    </template>
    <b-form-input></b-form-input>
  </b-input-group>
</div>
  </div>
</template>

<script>
export default {



}
</script>

<style scoped>
#searchbar {
  position:absolute;
  border-color: hsl(220, 9%, 87%);
  border: 1px;
 top:29px; 
   left:24px; 
  margin-left: 20px;
  width: 348px;
  height: 48px;
  border-radius: 8px;
  padding: 12px 15px;

}

.input-group-text {
  background-color: hsl(0, 0%, 100%);
  border:0px
}
</style>